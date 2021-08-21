from builtins import __import__

SCRIPTS_LOCATION = "files"

input_file = input("Enter python file name: ")
input_added_code = input("Enter python code: ")

#input_file = "fruit"
#input_added_code = "print('Hello')"

# For __str__ and __init__ change the function, so it calls the decorator. Remove __init__ if you want.
added_code_built_ins_change = ["__str__", "__init__"]

# Evil decor executes user input and then calls the original function.
def my_evil_decor(func):
    def decor_function(*args, **named_args):
        print("Decor is called on: ", str(func.__code__))
        eval(input_added_code)  # Execute given code from user.
        return func(*args, **named_args)

    return decor_function


if input_file.endswith(".py"):
    input_file = input_file.replace(".py", "")

module = __import__(f"{SCRIPTS_LOCATION}.{input_file}")  # Import fruit.py for example.

# We can do module.fruit statically, but it won't work if we do: module.input_file
# So we evaluate it dynamically in run time
inner_module = eval(f"module.{input_file}")
for _class_str in dir(inner_module):
    if (not _class_str.startswith("__")) and (not _class_str.endswith("__") and _class_str.lower() != "main"):
        e = eval(f"inner_module.{_class_str}")

        # If not class, continue.
        if not str(type(e)).__contains__("class"):
            continue

        # Else, get the class.
        _class = eval(f"inner_module.{_class_str}")

        # Traverse functions of the class.
        for _fun in dir(_class):

            # Do not change functions such as __class__ or __dir__. Allow only specific functions.
            if not (_fun.startswith("__") and _fun.endswith("__")) or _fun in added_code_built_ins_change:

                # Change the class function - add our evil decor.
                # Here we use EXEC instead of EVAL because we ASSIGN instead of EVALUATING EXPRESSIONS.
                exec_str = f"_class.{_fun} = my_evil_decor(_class.{_fun})"

                # Try to modify the function.
                try:
                    exec(exec_str)
                    print("Executed: " + exec_str)
                except:
                    # If the class is of type 'list' lets say (rain.py), we can't modify it, it's read only. So we catch these outliers.
                    pass

# Call the script's main function and see the changes the decor did.
print("Executing module main")

inner_module.main()

print("Finished executing meta.py .")
