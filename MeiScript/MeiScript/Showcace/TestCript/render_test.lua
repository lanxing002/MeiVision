mat = init()
mat2 = init()
mat:open("C:/Users/scent_wen/Pictures/test.jpg")
mat2:open("C:/Users/scent_wen/Pictures/t2.jpg")
print(mat.id)

--mat:show()

mat:show()
sleep(1000)
mat2:show()
sleep(1000)
mat:show()



--���ʲ���
--mat:set_pen({width = 20, color={r=255},rotate=90})
mat:set_pen({width = 20, color={r=255, b= 80},fill_color={r=255}, translate={0, 0}, rotate=0})

--���ֲ���

mat:render_text(120, 120, "�Ұ���") -- ���Ĳ���
sleep(1000)
mat:render_text(120, 140, "I love you") -- Ӣ�Ĳ���
sleep(1000)
mat:render_text(120, 160, "�ۣ����������Ƥ�") --���İ�
sleep(1000)

--���߲���
mat:render_line(110, 90, 280, 90)
sleep(1000)
mat:render_line(110, 90, 110, 180)
sleep(1000)
mat:render_line(110, 180, 280, 180)
sleep(1000)

--����β���
mat:set_pen({translate={200, 200}, rotate=40})
mat:render_polygon({{400, 80}, {600, 80}, {400, 200}, {400, 80}})
mat:save("C:/Users/scent_wen/Pictures/render_test.bmp") -- bmp�����ʽ





