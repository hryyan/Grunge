# inject方法让你遍历收集的所有成员以累计一个值。
# puts [1, 3, 5, 7].inject(0) {|sum, element| sum + element}

# block第一次被执行的时候，sum为inject函数的参数
# 每次进入block，第一个参数是上次block的返回值
# element是each的值

# 在Ruby中，迭代器集成于collection内部————它只不过是方法
# 与其他语言不同的是，每当产生新的值的时候调用yield。
# block来使用迭代器

# *args收集所有参数到名字为args的数组中。然后调用方法的时候，可以直接调用数组
# 打开文件之后，yield内容，并且在返回之后负责关闭文件
# 这样文件的关闭责任就从使用者变成文件本身了
# def openFile(*args)
# 	f = File.open(*args)
# 	yield f
# 	f.close()
# end

# block可以作为闭包
# 如果定义方法时，在最后一个参数前加上一个&，那么当调用该方法时。
# Ruby会寻找一个block，block会被转化成Proc类的一个对象，并赋值给参数。
# 当我们创建Proc类对象的时候，保存了定义block时的上下文环境
# 即使定义的环境已经消失了，block仍然可以使用其作用域中的信息。

# class Calc
# 	def initialize(&action)
# 		@action = action
# 	end
# 	def press
# 		@action.call(self)
# 	end
# end

# b = 10
# a = Calc.new() {puts b}
# a.press

# lambda加block可以生成一个Proc类的对象。
# def n_times(thing)
# 	return lambda { |n| thing * n }
# end

# p1 = n_times(20)
# puts p1.call(5)
# puts p1.call(4)
# p2 = n_times('Hello ')
# puts p2.call(3)

# 使用6.times加block代替for x in 0...6
# 数值的类型随着变大而改变
# num = 81
# 6.times do
# 	puts "#{num.class}: #{num}"
# 	num *= num
# end

# 所有数字都是对象，都能调用方法
# puts -999.abs

# upto和downto迭代器在两个整数之间分别向上和向下迭代
# 1.upto(5) {|i| puts i}
# 9.downto(1) {|i| puts i}
# 50.step(80, 5) {|i| puts i}

# 正则表达式是Regexp类型的对象。可以通过显式地调用构造函数或使用字面量形式
# /pattern/和%r{pattern}来创建它们

# a = Regexp.new('^\s*[a-z]')
# b = /^\s*[a-z]/
# c = %r{^\s*[a-z]}

# 可以使用Regexp#match或者操作匹配符=~（肯定匹配）和!~（否定匹配）对字符串进行匹配
# 匹配操作符对String和Regexp对象均有定义。匹配操作符至少有一个操作数必须为正则表达式

# name = "Fats Waller"
# puts name =~ /a/
# puts /a/ =~ name
# puts name !~ /z/

# $& 得到与模式匹配的那部分字符串，$`得到匹配之前的字符串，$'得到匹配之后那部分字符串

# def show_regexp(a, re)
# 	if a =~ re
# 		"#{$`}<<#{$&}>>#{$'}"
# 	else
# 		"no match"
# 	end
# end

# puts show_regexp('very interesting', /t/)
# puts show_regexp('Fats Waller', /a/)
# puts show_regexp('Fats Waller', /z/)

# Ruby不像Python那样严格要求缩进
# 使用内置变量block_given?可以判断是否有block联结在函数上
# def take_block(p1)
# 	if block_given?
# 		yield(p1)
# 	else
# 		p1
# 	end	
# end

# puts take_block("no block")
# puts take_block("no block") {|s| s.sub(/no /, '')}

# 关联的block会被转换为一个Pro对象，这是一个带参数的范例
# class TaxCalculator
# 	def initialize(name, &block)
# 		@name, @block = name, block
# 	end
# 	def get_tax(amount)
# 		"#@name on #{amount} = #{@block.call(amount)}"
# 	end
# end

# tc = TaxCalculator.new("Sales tax") {|amt| amt * 0.075}

# puts tc.get_tax(100)
# puts tc.get_tax(250)

# 方法调用中的数组展开
# 在数组元素前加入一个星号就可以完成展开

# def five(a, b, c, d, e)
# 	puts "I was passed #{a}, #{b}, #{c}, #{d}, #{e}"
# end

# five(1, 2, 3, 4, 5)
# five(1, 2, 3, *['a', 'b'])
# five(*(10..14).to_a)

# 因为任何东西都是对象，所以可以重新定义任何的基本方法

# class Fixnum
# 	alias old_plus + # reference the original '+' as 'old_plus'

# 	# Redefine addition of Fixnum.
# 	def +(other)
# 		old_plus(other).succ
# 	end
# end

# puts 1 + 2
# puts a = 3
# puts a += 4
# puts a + a + a