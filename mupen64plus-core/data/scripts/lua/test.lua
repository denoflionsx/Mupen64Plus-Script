--quick test/example script
print("This is test.lua running in", _VERSION)
for k, v in pairs(m64p) do print("m64p", k, v) end


local function hexdump(str, base, fmt)
	base = base or 0
	fmt  = fmt  or '%04X'
	for y = 0, #str-1, 16 do
		local buf = {fmt:format(base+y)}

		--print hex
		for x = 0, 15 do
			local a = x + y + 1
			buf[#buf+1] = ((x % 4) == 0) and "|" or " "

			local b = str:byte(a)
			if b then buf[#buf+1] = ('%02X'):format(b)
			else buf[#buf+1] = '..'
			end
		end

		--print ASCII
		buf[#buf+1] = '|'
		for x = 0, 15 do
			local a = x + y + 1
			local b = str:byte(a)
			if b and (b >= 0x20 and b <= 0x7E) then buf[#buf+1] = str:sub(a, a)
			else buf[#buf+1] = '.'
			end
		end

		print(table.concat(buf)) --output the buffer
	end
end