class AppleBasket:
    def __init__(self, color: str, amount: int):
        self.color_apple = color
        self.quantity_apple = amount

    def increase(self):
        self.quantity_apple += 1

    def __str__(self):
        return f"A basket of {self.quantity_apple} {self.color_apple} apples."


example1 = AppleBasket("red", 4)
example2 = AppleBasket("blue", 50)

print(example1)
print(example2)
