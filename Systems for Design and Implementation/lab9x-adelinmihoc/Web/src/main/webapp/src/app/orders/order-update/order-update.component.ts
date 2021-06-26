import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {ActivatedRoute, Router} from "@angular/router";
import {OrderService} from "../shared/order.service";

@Component({
  selector: 'app-order-update',
  templateUrl: './order-update.component.html',
  styleUrls: ['./order-update.component.css']
})
export class OrderUpdateComponent implements OnInit {
  orderUpdateForm!: FormGroup;
  orderId = 0;
  orderStatus = "";

  constructor(private router: Router, private route: ActivatedRoute, private orderService: OrderService) {
    const navigation = this.router.getCurrentNavigation();
    if (navigation != null) {
      const state = navigation.extras.state as {
        oid: number,
        ostatus: string,
      };
      console.log(state);
      this.orderId = state.oid;
      this.orderStatus = state.ostatus;
    }
  }

  ngOnInit(): void {
    this.orderUpdateForm = new FormGroup({
      id: new FormControl(this.orderId,[
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ]),
      status: new FormControl(this.orderStatus, [
        Validators.required,
        Validators.pattern('^[a-zA-Z]*$')
      ])
    });
  }

  onSubmit(form: FormGroup) {
    if (form.valid) {
      this.orderService.changeStatus(form.value.id, form.value.status);
    } else {
      alert("please enter a valid order");
    }
  }


  get id() {
    return this.orderUpdateForm.get('id');
  }

  get status() {
    return this.orderUpdateForm.get('status');
  }

}
