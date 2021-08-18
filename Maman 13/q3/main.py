class Person:
	def __init__(self, name: str, occupation: str):
		self.name = name
		self.occupation = occupation
	def __str__(self):
		return "Name: " + self.name + ", Occupation: " + self.occupation		



class Engineer(Person):
	def __init__(self, name: str):
		super().__init__(name, "engineer")
    
class Technician(Person):
	def __init__(self, name: str):
		super().__init__(name, "technician")

class Barber(Person):
	def __init__(self, name: str):
		super().__init__(name, "barber")

class Politician(Person):
	def __init__(self, name: str):
		super().__init__(name, "politician")




class ElectricEngineer(Engineer):
	def __init__(self, name: str):
		super().__init__(name, "electric engineer")

class ComputerEngineer(Engineer):
	def __init__(self, name: str):
		super().__init__(name, "computer engineer")

class MachineEngineer(Engineer):
	def __init__(self, name: str):
		super().__init__(name, "machine engineer")


input_class = input("Please enter the name of the new class: ")
input_base_class = input("Please enter name of base class (blank if none): ")
input_method = input(f"Please enter name of new method for class {input_class}: ")
input_abc = input(f"Please enter name of new attribute for class {input_class}: ")

