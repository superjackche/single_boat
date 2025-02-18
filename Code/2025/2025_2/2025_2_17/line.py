# 导包，导入Line功能构建折线图对象
from pyecharts.charts import Line
import pyecharts.options as opts
from pyecharts.options import ToolboxOpts, VisualMapOpts

# 得到折线图对象
line = Line()
# 添加x、y轴数据
line.add_xaxis(["a", "b", "c"])
line.add_yaxis("GDP", [10, 30, 20])
# 设置全局配置项
line.set_global_opts(
    title_opts=opts.TitleOpts(title="GDP Line Chart", subtitle="Example Subtitle", pos_bottom="1%", pos_left="center"),
    legend_opts=opts.LegendOpts(is_show=True),
    toolbox_opts=ToolboxOpts(is_show=True),
    visualmap_opts=VisualMapOpts(is_show=True, type_="color", min_=0, max_=30)
)
# 生成图表
line.render()