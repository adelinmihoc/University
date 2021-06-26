import { Component, OnInit } from '@angular/core';
import {Customer} from "../../customers/shared/customer.model";
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {CustomerService} from "../../customers/shared/customer.service";
import {Order} from "../shared/order.model";
import {OrderService} from "../shared/order.service";
import {Coffee} from "../../coffees/shared/coffee.model";

@Component({
  selector: 'app-order-filter',
  templateUrl: './order-filter.component.html',
  styleUrls: ['./order-filter.component.css']
})
export class OrderFilterComponent implements OnInit {
  orders!: Order[];
  coffees!: Coffee[];
  orderFilterForm = new FormGroup({
    customerId: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ])
  });

  constructor(private orderService: OrderService) {
  }

  ngOnInit(): void {
  }

  get customerId() {
    return this.orderFilterForm.get('customerId');
  }

  onSubmitFilterCustomerOrders(form: FormGroup) {
    if (form.valid) {
      this.orderService.filterCustomerOrders(form.value.customerId)
        .subscribe(orders => this.orders = orders);
    } else {
      alert("please enter a valid id");
    }
  }

  onSubmitFilterCustomerCoffees(form: FormGroup) {
    if (form.valid) {
      this.orderService.filterCustomerCoffees(form.value.customerId)
        .subscribe(coffees => this.coffees = coffees);
    } else {
      alert("please enter a valid id");
    }
  }

}
