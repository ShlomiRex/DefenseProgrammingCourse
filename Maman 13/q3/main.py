class Person:
    def __init__(self, name: str, occupation: str):
        self.name = name
        self.occupation = occupation

    def __str__(self):
        return "Name: " + self.name + ", Occupation: " + self.occupation


class Engineer(Person):
    def __init__(self, name: str, engineer_type: str = ""):
        _type = (engineer_type + " Engineer") if engineer_type else "Engineer"  # If type is empty don't use space
        super().__init__(name, _type)


class Technician(Person):
    def __init__(self, name: str):
        super().__init__(name, "Technician")


class Barber(Person):
    def __init__(self, name: str):
        super().__init__(name, "Barber")


class Politician(Person):
    def __init__(self, name: str):
        super().__init__(name, "Politician")


class ElectricEngineer(Engineer):
    def __init__(self, name: str):
        super().__init__(name, "Electric")


class ComputerEngineer(Engineer):
    def __init__(self, name: str):
        super().__init__(name, "Computer")


class MachineEngineer(Engineer):
    def __init__(self, name: str):
        super().__init__(name, "Machine")


# print(Person("Shlomi", "Self Employed Engineer"))
# print(Engineer("Shlomi"))
# print(ElectricEngineer("Shlomi"))
# print(MachineEngineer("Shlomi"))
# print(ComputerEngineer("Shlomi"))


input_class_name = input("Please enter the name of the new class: ")
input_base_class = input("Please enter name of base class (blank if none): ")
input_method_name = input(f"Please enter name of new method for class '{input_class_name}': ")
input_attr = input(f"Please enter name of new attribute for class '{input_class_name}': ")

# input_class_name = "Student"
# input_base_class = "Politician"
# input_method_name = "homework"
# input_attr = "Major"

if input_base_class == "Person":
    bases = (Person,)
elif input_base_class == "Politician":
    bases = (Politician,)
else:
    print("Couldn't find the base class: " + input_base_class)
    exit(1)


def dummy():
    print("Dummy function")


NewClass = type(input_class_name, bases, {
    input_method_name: dummy,
    input_attr: "dummy attribute value"
})

print(f"Class {NewClass.__name__} created with base class: {input_base_class}")
print(f"Class __name__ is: {NewClass.__name__}")
print(f"Class __dict__ is: {NewClass.__dict__}")
print(f"Class hierarchy: {NewClass.__mro__}")
