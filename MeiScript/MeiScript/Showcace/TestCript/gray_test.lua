mat = init()
mat:open("C:/Users/scent_wen/Pictures/test.jpg")
--gray_scale ����
mat2 = mat:grayscale() --����һ���Ҷ�ͼ��
print(mat2.id)
print(mat.width == mat2.width)
print(mat.height == mat2.height)
print(mat.depth == mat2.depth)

mat:show()