mat = init()
mat:open("D:24997475.bmp")
print(mat.id)
mat:show()

for i = 0, mat.height - 1, 1 do
    for j = 0, mat.width - 1, 1 do
        co = mat:at(i, j)
        if co.r == 255 and co.g == 255 and co.b==255 then 
            mat:write(i, j, {r=255, g=0, b=0})
        end
    end
    sleep(100)
end