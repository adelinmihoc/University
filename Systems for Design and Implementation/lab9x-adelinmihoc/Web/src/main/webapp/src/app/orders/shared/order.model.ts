import {Customer} from "../../customers/shared/customer.model";

export class Order {
  id!:number;
  status!: string;
  localDateTime!: string;
  customer!: Customer;
}
