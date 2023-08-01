--[=[

This is a test script for the scripting system. It is loaded by the script manager and
executed when the mud starts up.

Scripts should not do much work in the global scope that will be executed when the script
is loaded. Initialization should take place in the on_init() callback.

The script can access the builtin Lua libraries string, table, math, io, utf8, and require.
I absolutely cannot be bothered to implement coroutine compatibility.

A script can implement callback functions that will be called by the script manager:

  on_init() - called when the script is loaded
  on_close() - called when the script is unloaded
  on_tick() - called every tick

The script should end with a return statement that returns a table of metadata.

return {
  name = "slot_machine",
  version = "1.0",
  description = "Slot machine game",
  author = "Barry Scripto",
  commands = {
    slots = "do_slots",
    tokens = "do_tokens",
    cashout = "do_cashout"
  },
  helps = {
    {
      level = 18, -- gambling isn't for minors, after all
      keywords = "slots tokens cashout",
      text = [[
        Used to play the slot machines.
          slots - play the slot machines
          tokens - check your token balance
          cashout - exchange your tokens for prizes
      ]]
    }
  }
}

--]=]

function on_init()
  mud.log("scrtest -- on_init")
end

function on_close()
  mud.log("scrtest -- on_close")
end

function tprint (tbl, indent)
  if not indent then indent = 0 end
  local toprint = string.rep(" ", indent) .. "{\r\n"
  indent = indent + 2
  for k, v in pairs(tbl) do
    toprint = toprint .. string.rep(" ", indent)
    if (type(k) == "number") then
      toprint = toprint .. "[" .. k .. "] = "
    elseif (type(k) == "string") then
      toprint = toprint  .. k ..  "= "
    end
    if (type(v) == "number") then
      toprint = toprint .. v .. ",\r\n"
    elseif (type(v) == "string") then
      toprint = toprint .. "\"" .. v .. "\",\r\n"
    elseif (type(v) == "table") then
      toprint = toprint .. tprint(v, indent + 2) .. ",\r\n"
    else
      toprint = toprint .. "\"" .. tostring(v) .. "\",\r\n"
    end
  end
  toprint = toprint .. string.rep(" ", indent-2) .. "}"
  return toprint
end

function do_scrtest(ch, args)
  mud.send_char("scrtest -- doing it: " .. args, ch)
  mud.log("scrtest -- doing it: " .. args)
end

function help_scrtest()
  return "Usage: scrtest <any>"
end

return {
  name = "scrtest",
  description = "Script runtime testing script",
  commands = {
    scrtest = do_scrtest,
    scrtoo = "do_scrtest",
    scrthree = "do_none"
  },
  helps = {
    {
      level = 0,
      keywords = "scrtest",
      text = help_scrtest()
    },
    {
      level = 0,
      keywords = "scripting",
      text = "This is the help text for 'scripting'."
    }
  }
}
