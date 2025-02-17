# 导包，导入Line功能构建折线图对象
from pyecharts.charts import Line

# 得到折线图对象
line = Line()
# 添加x、y轴数据
line.add_xaxis(["a", "b", "c"])
line.add_yaxis("GDP",[10, 30, 20])
# 生成图表
line.render()