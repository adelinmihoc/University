import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {Customer} from "../shared/customer.model";
import {CustomerService} from "../shared/customer.service";
import {AddressService} from "../../addresses/shared/address.service";
import {Address} from "../../addresses/shared/address.model";

@Component({
  selector: 'app-customer-add',
  templateUrl: './customer-add.component.html',
  styleUrls: ['./customer-add.component.css']
})
export class CustomerAddComponent implements OnInit {
  customerAddForm = new FormGroup({
    firstName: new FormControl('', [
      Validators.required,
      Validators.pattern('^[a-zA-Z]*$')
    ]),
    lastName: new FormControl('', [
      Validators.required,
      Validators.pattern('^[a-zA-Z]*$')
    ]),
    phoneNumber: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ]),
    age: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ]),
    addressId: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ])
  });

  constructor(private customerService: CustomerService) { }

  ngOnInit(): void {
  }

  onSubmit(form: FormGroup) {
    if (form.valid) {
      const address: Address = <Address>{id: form.value.addressId};
      const customer: Customer = <Customer>{
        firstName: form.value.firstName,
        lastName: form.value.lastName, phoneNumber: form.value.phoneNumber,
        age: form.value.age, address: address};
      this.customerService.saveCustomer(customer).subscribe(v => console.log(v));
    } else {
      alert("please enter a valid customer");
    }
  }


  get firstName() {
    return this.customerAddForm.get('firstName');
  }

  get lastName() {
    return this.customerAddForm.get('lastName');
  }

  get phoneNumber() {
    return this.customerAddForm.get('phoneNumber');
  }

  get age() {
    return this.customerAddForm.get('age');
  }

  get addressId() {
    return this.customerAddForm.get('addressId');
  }
}
