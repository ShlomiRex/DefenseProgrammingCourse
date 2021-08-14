class BankAccount:
    def __init__(self, account_name: str, balance_left: int):
        self.name = account_name
        self.amt = balance_left

    def __str__(self):
        return f"Your account, {self.name}, has {self.amt} dollars."


t1 = BankAccount("Bob", 100)
print(t1)
