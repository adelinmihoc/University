import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";
import {OrderService} from "../shared/order.service";
import {CoffeeService} from "../../coffees/shared/coffee.service";
import {CustomerService} from "../../customers/shared/customer.service";
import {FormControl, FormGroup, Validators} from "@angular/forms";

@Component({
  selector: 'app-order-add',
  templateUrl: './order-add.component.html',
  styleUrls: ['./order-add.component.css']
})
export class OrderAddComponent implements OnInit {
  orderID = 0;
  orderAddToForm!: FormGroup;

  orderAddForm = new FormGroup({
    customerId: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ])
  });


  constructor(private router: Router, private orderService: OrderService) {
    const navigation = this.router.getCurrentNavigation();
    if (navigation != null) {
      const state = navigation.extras.state as {
        oid: number,
      };
      console.log(state);
      this.orderID = state.oid;
    } }

  ngOnInit(): void {
    this.orderAddToForm = new FormGroup({
      orderId: new FormControl(this.orderID, [
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ]),
      coffeeId: new FormControl('', [
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ])
    });
  }

  onSubmitAdd(form: FormGroup) {
    console.log("valid?", form.valid);
    console.log("customerId ", form.value.customerId);
    if (form.valid) {
      this.orderService.saveOrder(form.value.customerId);
    } else {
      alert("please enter a valid id");
    }
  }

  onSubmitAddTo(form: FormGroup) {
    if (form.valid) {
      this.orderService.addCoffee(form.value.orderId, form.value.coffeeId);
    } else {
      alert("please enter valid ids");
    }
  }

  get customerId() {
    return this.orderAddForm.get('customerId');
  }

  get orderId() {
    return this.orderAddToForm.get('orderId');
  }

  get coffeeId() {
    return this.orderAddToForm.get('coffeeId');
  }
}
