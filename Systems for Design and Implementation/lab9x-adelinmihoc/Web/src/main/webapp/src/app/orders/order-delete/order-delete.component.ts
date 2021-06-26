import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {AddressService} from "../../addresses/shared/address.service";
import {OrderService} from "../shared/order.service";

@Component({
  selector: 'app-order-delete',
  templateUrl: './order-delete.component.html',
  styleUrls: ['./order-delete.component.css']
})
export class OrderDeleteComponent implements OnInit {
  orderDeleteForm = new FormGroup({
    id: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ])
  });

  constructor(private orderService: OrderService) {
  }

  ngOnInit(): void {
  }

  onSubmitDeleteById(form: FormGroup) {
    if (form.valid) {
      this.orderService.deleteOrder(form.value.id);
    } else {
      alert("please enter a valid id");
    }
  }

  get id() {
    return this.orderDeleteForm.get('id');
  }
}

