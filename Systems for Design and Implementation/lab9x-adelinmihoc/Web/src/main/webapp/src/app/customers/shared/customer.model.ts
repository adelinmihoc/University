import {Address} from "../../addresses/shared/address.model";

export class Customer {
  id!: number;
  firstName!: string;
  lastName!: string;
  phoneNumber!: string;
  age!: number;
  address!: Address;
}
