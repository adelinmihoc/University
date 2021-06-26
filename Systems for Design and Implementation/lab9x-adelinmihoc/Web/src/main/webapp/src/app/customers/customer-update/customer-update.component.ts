import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {ActivatedRoute, Router} from "@angular/router";
import {Address} from "../../addresses/shared/address.model";
import {Customer} from "../shared/customer.model";
import {CustomerService} from "../shared/customer.service";

@Component({
  selector: 'app-customer-update',
  templateUrl: './customer-update.component.html',
  styleUrls: ['./customer-update.component.css']
})
export class CustomerUpdateComponent implements OnInit {
  customerUpdateForm!: FormGroup;
  customerId = 0;
  customerFirstName = "";
  customerLastName = "";
  customerPhoneNumber = 0;
  customerAge = 0;
  customerAddressId = 0;

  constructor(private router: Router, private route: ActivatedRoute, private customerService: CustomerService) {
    const navigation = this.router.getCurrentNavigation();
    if (navigation != null) {
      const state = navigation.extras.state as {
        cid: number,
        cfirstname: string,
        clastname: string,
        cphonenumber: number
        cage: number
        caddressid: number
      };
      console.log(state);
      this.customerId = state.cid;
      this.customerFirstName = state.cfirstname;
      this.customerLastName = state.clastname;
      this.customerPhoneNumber = state.cphonenumber;
      this.customerAge = state.cage;
      this.customerAddressId = state.caddressid;
    }
  }

  ngOnInit(): void {
    this.customerUpdateForm = new FormGroup({
      id: new FormControl(this.customerId,[
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ]),
      firstName: new FormControl(this.customerFirstName, [
        Validators.required,
        Validators.pattern('^[a-zA-Z]*$')
      ]),
      lastName: new FormControl(this.customerLastName, [
      Validators.required,
      Validators.pattern('^[a-zA-Z]*$')
    ]),
      phoneNumber: new FormControl(this.customerPhoneNumber, [
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ]),
      age: new FormControl(this.customerAge, [
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ]),
      addressId: new FormControl(this.customerAddressId, [
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ])
    });
  }

  onSubmit(form: FormGroup) {
    console.log("valid?", form.valid);
    console.log("id ", form.value.id);
    console.log("firstName ", form.value.firstName);
    console.log("lastName ", form.value.lastName);
    console.log("phoneNumber ", form.value.phoneNumber);
    console.log("age ", form.value.age);
    console.log("addressId ", form.value.addressId);
    if (form.valid) {
      const address: Address = <Address>{id: form.value.addressId};
      const customer: Customer = <Customer>{
        id: form.value.id, firstName: form.value.firstName, lastName: form.value.lastName,
        phoneNumber: form.value.phoneNumber, age: form.value.age, address: address};
      this.customerService.updateCustomer(customer);
    } else {
      alert("please enter a valid customer")
    }
  }

  get id() {
    return this.customerUpdateForm.get('id');
  }

  get firstName() {
    return this.customerUpdateForm.get('firstName');
  }

  get lastName() {
    return this.customerUpdateForm.get('lastName');
  }

  get phoneNumber() {
    return this.customerUpdateForm.get('phoneNumber');
  }

  get age() {
    return this.customerUpdateForm.get('age');
  }

  get addressId() {
    return this.customerUpdateForm.get('addressId');
  }
}
