require 'busted.runner'()

local assert = require 'spec.assert'
local config = require 'euluna.configer'.get()
local n = require 'euluna.syntaxdefs'().astbuilder.aster

describe("Euluna should check types for", function()

it("local variable", function()
  assert.analyze_ast("local a: integer",
    n.Block { {
      n.VarDecl { 'local', 'var',
        { n.IdDecl{ assign=true, type='int64', 'a', 'var',
          n.Type { type='int64', 'integer'}}}
      }
    } }
  )

  assert.analyze_ast("local a: integer = 1",
    n.Block { {
      n.VarDecl { 'local', 'var',
        { n.IdDecl{ assign=true, type='int64', 'a', 'var',
          n.Type { type='int64', 'integer'}}},
        { n.Number{ literal=true, type='int64', 'dec', '1'}}
      }
    } }
  )

  assert.analyze_ast("local a = 1; f(a)",
    n.Block { {
      n.VarDecl { 'local', 'var',
        { n.IdDecl { assign=true, type='int64', 'a', 'var' }},
        { n.Number { literal=true, type='int64', 'dec', '1' }}
      },
      n.Call { callee_type='any', type='any',
        { n.Id { type='int64', "a"} },
        n.Id { type='any', "f"},
        true
    }
  }})

  assert.c_gencode_equals("local a = 1", "local a: integer = 1")
  assert.analyze_error("local a: integer = 'string'", "is not conversible with")
  assert.analyze_error("local a: uint8 = 1.0", "is not conversible with")
  assert.analyze_error("local a: uint8 = {1.0}", "cannot be initialized using a table literal")
end)

it("typed var initialization", function()
  assert.lua_gencode_equals("local a: integer", "local a: integer = 0")
  assert.lua_gencode_equals("local a: boolean", "local a: boolean = false")
  assert.lua_gencode_equals("local a: arraytable<integer>", "local a: arraytable<integer> = {}")
end)

it("loop variables", function()
  assert.c_gencode_equals("for i=1,10 do end", "for i:integer=1,10 do end")
  assert.c_gencode_equals("for i=1,10,2 do end", "for i:integer=1,10,2 do end")
  assert.c_gencode_equals("for i=0_i,1_i-1 do end", "for i:integer=0_i,1_i-1 do end")
  assert.analyze_error("for i:uint8=1.0,10 do end", "is not conversible with")
  assert.analyze_error("for i:uint8=1_u8,10 do end", "is not conversible with")
  assert.analyze_error("for i:uint8=1_u8,10_u8,2 do end", "is not conversible with")
end)

it("variable assignments", function()
  assert.c_gencode_equals("local a; a = 1", "local a: integer; a = 1")
  assert.analyze_error("local a: integer; a = 's'", "is not conversible with")
end)

it("unary operators", function()
  assert.c_gencode_equals("local a = not b", "local a: boolean = not b")
  assert.c_gencode_equals("local a = -1", "local a: integer = -1")
  assert.analyze_error("local a = -1_u", "is not defined for type")
end)

it("binary operators", function()
  assert.c_gencode_equals("local a = 1 + 2", "local a: integer = 1 + 2")
  assert.c_gencode_equals("local a = 1 + 2.0", "local a: number = 1 + 2.0")
  assert.c_gencode_equals("local a = 1_i8 + 2_u8", "local a: int16 = 1_i8 + 2_u8")
  assert.analyze_error("local a = 1 + 's'", "is not defined for type")
  assert.analyze_error("local a = -1_u", "is not defined for type")
end)

it("binary conditional operators", function()
  assert.c_gencode_equals("local a = 1 and 2", "local a: integer = 1 and 2")
  assert.c_gencode_equals("local a = 1_i8 and 2_u8", "local a: int16 = 1_i8 and 2_u8")
end)

it("operation with parenthesis", function()
  assert.c_gencode_equals("local a = -(1)", "local a: integer = -(1)")
end)

it("recursive late deduction", function()
  assert.c_gencode_equals([[
    local a, b, c
    a = 1
    b = 2
    c = a + b
  ]],[[
    local a:integer, b:integer, c:integer
    a = 1
    b = 2
    c = a + b
  ]])
  assert.c_gencode_equals([[
    local a = 1_integer
    local b = a + 1
  ]],[[
    local a: integer = 1_integer
    local b: integer = a + 1
  ]])
  assert.c_gencode_equals([[
    local limit = 1_integer
    for i=1,limit do end
  ]],[[
    local limit = 1_integer
    for i:integer=1,limit do end
  ]])
end)

it("function definition", function()
  assert.analyze_ast([[
    local f
    function f() end
  ]])
  assert.analyze_ast([[
    local function f(a: integer) end
    function f(a: integer) end
  ]])
  assert.analyze_ast([[
    local f: function<(integer): string>
    function f(a: integer): string end
  ]])
  assert.analyze_error([[
    local f: int
    function f(a: integer) return 0 end
  ]], "is not conversible with")
  assert.analyze_error([[
    local function f(a: integer) end
    function f(a: integer, b:integer) end
  ]], "is not conversible with")
  assert.analyze_error([[
    local function f(a: integer) end
    function f(a: string) end
  ]], "is not conversible with")
  assert.analyze_error([[
    local function f(): integer, string end
    function f(): integer end
  ]], "is not conversible with")
  assert.analyze_error([[
    local f: function<():integer, string>
    function f(): integer end
  ]], "is not conversible with")
end)

it("function return", function()
  assert.c_gencode_equals(
    "local function f() return 0 end",
    "local function f(): integer return 0 end"
  )
  assert.c_gencode_equals([[
    local function f()
      local a, b, c
      a = 1; b = 2; c = a + b
      return c
    end
    ]],[[
    local function f(): integer
      local a: integer, b: integer, c: integer
      a = 1; b = 2; c = a + b
      return c
    end
  ]])
  assert.analyze_error([[
    local function f(): string return 0 end
  ]], "is not conversible with")
end)

it("function call", function()
  assert.c_gencode_equals([[
    local function f() return 0 end
    local a = f()
  ]],[[
    local function f(): integer return 0 end
    local a: integer = f()
  ]])
  assert.analyze_error([[
    local a: integer = 1
    a()
  ]], "attempt to call a non callable variable")
  assert.analyze_error([[
    local function f(a: integer) end
    f('a')
  ]], "is not conversible with")
end)

it("array tables", function()
  assert.analyze_ast([[
    local a: arraytable<boolean>
    local b: arraytable<boolean>
    b = a
  ]])
  assert.analyze_ast([[
    local a: arraytable<boolean>
    local len = #a
  ]])
  assert.analyze_ast([[
    local a: arraytable<boolean> = {}
    local b: arraytable<boolean> = {false, true}
    local c = @arraytable<boolean>{false, true}
  ]])
  assert.c_gencode_equals([[
    local a: arraytable<boolean>
    local b = a[0]
  ]],[[
    local a: arraytable<boolean>
    local b: boolean = a[0]
  ]])
  assert.analyze_error([[
    local a: arraytable<integer>
    local b: arraytable<boolean>
    b = a
  ]], "is not conversible with")
  assert.analyze_error([[
    local a: arraytable<integer> = {false}
  ]], "is not conversible with")
  assert.analyze_error([[
    local a: arraytable<integer> = {a = 1}
  ]], "fields are not allowed")
  assert.analyze_error([[
    local a: arraytable<boolean>
    local b: arraytable<integer>
    b = a
  ]], "is not conversible with")
end)

it("arrays", function()
  assert.analyze_ast([[local a: array<integer, 10>; a[0] = 1]])
  assert.analyze_ast([[local a: array<integer, 2> = {1,2}]])
  assert.analyze_ast([[local a: array<integer, 10>, b: array<integer, 10>; b = a]])
  assert.analyze_ast([[local a: arraytable<boolean>; local len = #a]])
  assert.analyze_error([[local a: array<integer, 2> = {1}]], 'expected 2 values but got 1')
  assert.analyze_error([[local a: array<integer, 2> = {1,2,3}]], 'expected 2 values but got 3')
  assert.analyze_error([[local a: array<integer, 2> = {1.0,2.0}]], 'is not conversible with')
  assert.analyze_error([[local a: array<integer, 2> = {a=0,2}]], 'fields are not allowed')
  assert.analyze_error([[
    local a: array<integer, 10>, b: array<integer, 11>
    b = a
  ]], "is not conversible with")
  assert.analyze_error([[
    local a: array<integer, 10>
    a[0] = 1.0
  ]], "is not conversible with")
  assert.analyze_error([[
    local a: array<integer, 1.0>
  ]], "expected a valid decimal integral number in the second argument")
  assert.analyze_error([[
    local MyArray = @array<integer, 10>
    local b = MyArray.len
  ]], "cannot index object of type")
end)

it("records", function()
  assert.analyze_ast([[local a: record {x: boolean}; a.x = true]])
  assert.analyze_ast([[local a: record {x: boolean} = {x = true}]])
  assert.analyze_ast([[local a: record {x: boolean}; local len = #a]])
  assert.analyze_error([[local a: record {x: boolean}; a.x = 1]], "is not conversible with")
  assert.analyze_error([[local a: record {x: boolean}; local b = a.y]], "does not have field named")
  assert.analyze_error([[local a: record {x: boolean} = {x = 1}]], "is not conversible with")
  assert.analyze_error([[local a: record {x: boolean} = {y = 1}]], "is not present in record")
  assert.analyze_error([[local a: record {x: boolean} = {[x] = 1}]], "only string literals are allowed")
  assert.analyze_error([[local a: record {x: boolean} = {false}]], "only named fields are allowed")
  assert.analyze_ast([[
    local Record: type = @record{x: boolean}
    local a: Record, b: Record
    b = a
  ]])
  assert.analyze_error([[
    local a: record {x: boolean}, b: record {x: boolean}
    b = a
  ]], "is not conversible with")
  assert.analyze_error([[
    local A, B = @record {x: boolean}, @record {x: boolean}
    local a: A, b: B
    b = a
  ]], "is not conversible with")
end)

it("enums", function()
  assert.analyze_ast([[
    local a: enum{A}
    local b: enum<integer>{A,B}
  ]])
  assert.analyze_ast([[
    local Enum = @enum{A,B=3}
    local e: Enum = Enum.A
    local i: number = e
  ]])
  assert.analyze_error([[
    local Enum = @enum{A,B=3}
    local e: Enum = Enum.A
    local i: string = e
  ]], "is not conversible with")
  assert.analyze_error([[
    local Enum = @enum{A,B}
    local e: Enum = Enum.C
  ]], "does not have field named")
  assert.analyze_error([[
    local Enum = @enum{A,B=3}
    local e: Enum = 1
  ]], "is not conversible with")
end)

it("pointers", function()
  assert.analyze_ast([[
    local a: pointer<integer>
    local b: pointer
    b = a
  ]])
  assert.analyze_ast([[
    local a: pointer<integer>
    local b: pointer<integer>
    b = a
  ]])
  assert.analyze_error([[
    local a: pointer<integer>
    local b: pointer<boolean>
    b = a
  ]], "is not conversible with")
  assert.analyze_error([[
    local a: pointer<integer>
    local b: pointer
    a = b
  ]], "is not conversible with")
end)

it("type construction", function()
  assert.analyze_ast("local a = @integer(0)")
  assert.analyze_ast("local a = @boolean(false)")
  assert.analyze_ast("local a = @string('')")
  assert.analyze_ast("local a = @any(nil)")
  assert.analyze_error("local a = @integer()", "expected one argument")
  assert.analyze_error("local a = @integer(1,2)", "expected one argument")
  assert.analyze_error("local a = @integer(false)", "is not conversible with")
  assert.analyze_error("local a = @integer(nil)", "is not conversible with")
end)

it("strict mode", function()
  config.strict = true
  assert.analyze_error("a = 1", "undeclarated symbol")
  assert.analyze_error("local a; local a", "shadows pre declarated symbol")
  config.strict = false
end)

end)