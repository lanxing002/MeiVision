mat = init()
mat:open("C:/Users/scent_wen/Pictures/cc_test.bmp")
mat2 = mat:grayscale()
mat2:show()
print(mat2.width)
print(mat2.height)
function is_connected(i, j) 
    co1 = mat2:at(i-1, j)
    co2 = mat2:at(i-1, j-1)
    co3 = mat2:at(i-1, j + 1)
    co4 = mat2:at(i, j - 1)
    if co1.r ~= 0 and co1.r ~= 255 then return true, co1.r end
    if co2.r ~= 0 and co2.r ~= 255 then return true, co2.r end 
    if co3.r ~= 0 and co3.r ~= 255 then return true, co3.r end
    if co4.r ~= 0 and co4.r ~= 255 then return true, co4.r end
    return false, -1
end

--0-1ÇøÓò
for i = 0, mat2.width - 1, 1 do
    for j = 0, mat2.height - 1, 1 do
        co = mat2:at(i, j)
        if (co.r < 100)  then mat2:write(i, j   , {r=0, g=0, b=0}) 
        else mat2:write(i, j, {r=255, g=255, b=255})
        end 
    end
end


cnt = 0
for i = 0, mat2.width - 1, 1 do
    for j = 0, mat2.height - 1, 1 do
       co = mat2:at(i, j)
       if (co.r == 0)  then
            f, index = is_connected(i, j)
            if (f) then mat2:write(i, j, {r=index, g=index, b=index})
            else cnt =cnt + 10 mat2:write(i, j, {r=cnt, g=cnt, b=cnt}) 
            end 
       end     
    end
end
mat2:save("C:/Users/scent_wen/Pictures/tt_gray.bmp")
