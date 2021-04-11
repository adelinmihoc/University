from Errors.Exceptions import AddressError


class ValidateAddress:
    @staticmethod
    def validate_address(address):
        errors = ""
        if address.get_id() < 0:
            errors += "Invalid id!\n"
        if len(address.get_name()) < 3:
            errors += "Invalid name!\n"
        if address.get_number() < 0 or address.get_number() > 100:
            errors += "Invalid number!\n"
        if len(errors) > 0:
            raise AddressError(errors)
