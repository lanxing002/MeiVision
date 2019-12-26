function Sleep(n)
   if n > 0 then os.execute("ping -n " .. tonumber(n + 1) .. " localhost > NUL") end
end

mat = init()
mat:open("D:24997475.bmp")
print(mat.id)
mat:show()

sleep(3000)

mat2 = init()
mat2:open("D:test.jpg")
print(mat.id)
mat:show()

for i = 1,300, 1 do
    for j = 1, 3, 1 do

            print(i)

    end
end

