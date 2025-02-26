class Student:
    name = None
    age = None
    gender = None
    nationality = None

    def say_hi(self):
        print(self.name)
        print(self.age)
        print(self.gender)
        print(self.nationality)

stu_01 = Student()
stu_02 = Student()

stu_01.name = 'Jack'
stu_01.age = 18
stu_01.gender = 'male'
stu_01.nationality = 'China'

stu_02.name = 'Jane'
stu_02.age = 16
stu_02.gender = 'female'
stu_02.nationality = 'China'

stu_01.say_hi()
stu_02.say_hi()