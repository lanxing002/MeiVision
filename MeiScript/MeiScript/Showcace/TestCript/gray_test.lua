mat = init()
mat:open("C:/Users/scent_wen/Pictures/test.jpg")
--gray_scale 测试
mat2 = mat:grayscale() --返回一个灰度图像
print(mat2.id)
print(mat.width == mat2.width)
print(mat.height == mat2.height)
print(mat.depth == mat2.depth)

mat:show()