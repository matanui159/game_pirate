local vertices = {}
local normals = {}
local groups = {}
local current = {}

local mesh = io.open("mesh.obj", "r")
for line in mesh:lines() do
	local name, x = line:match("(%S+) (%S+)")
	local y, z = line:match("%S+ %S+ (%S+) (%S+)")
	if name then
		if name == "v" then
			table.insert(vertices, {
				tonumber(x),
				tonumber(y),
				tonumber(z)
			})
		elseif name == "vn" then
			table.insert(normals, {
				tonumber(x),
				tonumber(y),
				tonumber(z)
			})
		elseif name == "usemtl" then
			if not groups[x] then
				groups[x] = {}
			end
			current = groups[x]
		elseif name == "f" then
			local function add_vertex(info)
				local v, n = info:match("(%d+)/%d+/(%d+)")
				v = vertices[tonumber(v)]
				n = normals[tonumber(n)]
				table.insert(current, v[1])
				table.insert(current, v[2])
				table.insert(current, v[3])
				table.insert(current, n[1])
				table.insert(current, n[2])
				table.insert(current, n[3])
			end
			add_vertex(x)
			add_vertex(y)
			add_vertex(z)
		end
	end
end
mesh:close()

local out = io.open(arg[1], "wb")

out:write([[
#ifndef MESH_DATA_H_
#define MESH_DATA_H_

]])

for mat, data in pairs(groups) do
	out:write("extern const int g_mesh_" .. mat .. "_size;\n")
	out:write("extern const float g_mesh_" .. mat .. "_data[];\n")
end

out:write([[

#endif
#ifdef MESH_DATA_BUILD

]])

for mat, data in pairs(groups) do
	out:write("const int g_mesh_" .. mat .. "_size = " .. #data .. ";\n")
	out:write("const float g_mesh_" .. mat .. "_data[] = {")
	for i, v in ipairs(data) do
		if i ~= 1 then
			out:write(", ")
		end
		out:write(v)
	end
	out:write("};\n\n")
end

out:write([[
#endif
]])
out:close()