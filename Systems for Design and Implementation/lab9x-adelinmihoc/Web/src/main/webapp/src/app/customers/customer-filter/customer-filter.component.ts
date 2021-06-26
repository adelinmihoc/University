import { Component, OnInit } from '@angular/core';
import {Customer} from "../shared/customer.model";
import {CustomerService} from "../shared/customer.service";
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {Address} from "../../addresses/shared/address.model";

@Component({
  selector: 'app-customer-filter',
  templateUrl: './customer-filter.component.html',
  styleUrls: ['./customer-filter.component.css']
})
export class CustomerFilterComponent implements OnInit {
  customers!: Customer[];
  customerFilterForm = new FormGroup({
    name: new FormControl('', [
      Validators.pattern('^[a-zA-Z]*$')
    ]),
    age1: new FormControl('', [
      Validators.pattern('^[0-9]*$')
    ]),
    age2: new FormControl('', [
      Validators.pattern('^[0-9]*$')
    ])
  });


  constructor(private customerService: CustomerService) { }

  ngOnInit(): void {
  }

  get name() {
    return this.customerFilterForm.get('name');
  }

  get age1() {
    return this.customerFilterForm.get('age1');
  }

  get age2() {
    return this.customerFilterForm.get('age2');
  }

  onSubmitFilterByName(form: FormGroup) {
    if (form.valid) {
      this.customerService.filterCustomersByName(form.value.name)
        .subscribe(customers => this.customers = customers);
    } else {
      alert("please enter a valid name");
    }
  }

  onSubmitFilterByAgeInterval(form: FormGroup) {
    this.customerService.filterCustomersByAgeInterval(form.value.age1, form.value.age2)
      .subscribe(customers => this.customers = customers);
  }

}
