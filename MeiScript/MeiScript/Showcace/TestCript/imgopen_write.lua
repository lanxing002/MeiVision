function Sleep(n)
   if n > 0 then os.execute("ping -n " .. tonumber(n + 1) .. " localhost > NUL") end
end

mat = init()
mat:open("D:24997475.bmp")
print(mat.id)
mat:show()



for i = 1,3000, 1 do
    for j = 1, 3000, 1 do
        if(j == 20) then 
            print(i)
        end
    end
end

