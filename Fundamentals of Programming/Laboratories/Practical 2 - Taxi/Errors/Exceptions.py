class RepoError(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class AddressError(Exception):
    def __init__(self, msg):
        super().__init__(msg)
