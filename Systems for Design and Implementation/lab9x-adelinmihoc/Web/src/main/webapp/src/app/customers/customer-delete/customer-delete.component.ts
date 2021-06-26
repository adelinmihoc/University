import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {AddressService} from "../../addresses/shared/address.service";
import {CustomerService} from "../shared/customer.service";

@Component({
  selector: 'app-customer-delete',
  templateUrl: './customer-delete.component.html',
  styleUrls: ['./customer-delete.component.css']
})
export class CustomerDeleteComponent implements OnInit {
  customerDeleteForm = new FormGroup({
    id: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ])
  });

  constructor(private customerService: CustomerService) { }

  ngOnInit(): void {
  }

  onSubmitDeleteById(form: FormGroup) {
    console.log("valid?", form.valid);
    console.log("id ", form.value.id);
    if (form.valid) {
      this.customerService.deleteCustomer(form.value.id);
    } else {
      alert("please enter a valid id");
    }
  }


  get id() {
    return this.customerDeleteForm.get('id');
  }


}
