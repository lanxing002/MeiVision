mat = init()
mat2 = init()
mat:open("C:/Users/scent_wen/Pictures/test.jpg")
mat2:open("C:/Users/scent_wen/Pictures/t2.jpg")
--mat:open("D:test.jpg")
print(mat.id)
mat:show()

for i = 0, mat.height - 1, 1 do
    for j = 0, mat.width - 1, 1 do
        co = mat:at(j, i)
--        if co.r == 255 and co.g == 255 and co.b == 255 then 
            mat:write(j, i, {g=co.g + 50})
--	   if(i == 50) then mat2:show() end

--        end
    end
--    sleep(100)
end