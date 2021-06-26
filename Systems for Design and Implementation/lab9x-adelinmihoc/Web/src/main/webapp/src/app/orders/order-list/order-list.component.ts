import { Component, OnInit } from '@angular/core';
import {Order} from "../shared/order.model";
import {OrderService} from "../shared/order.service";
import {Observable} from "rxjs";
import {Coffee} from "../../coffees/shared/coffee.model";
import {Router} from "@angular/router";

@Component({
  selector: 'app-order-list',
  templateUrl: './order-list.component.html',
  styleUrls: ['./order-list.component.css']
})
export class OrderListComponent implements OnInit {
  orders!: Order[];
  coffees!: Coffee[];

  constructor(private orderService: OrderService, private router: Router) { }

  ngOnInit(): void {
    this.orderService.getOrders()
      .subscribe(orders => {
        this.orders = orders;
        // orders.forEach(order => this.getOrderDetails(order.id)
        //   .subscribe(orderDetails => order.orderDetails = orderDetails));
      });
  }

  getOrderCoffees(oid: number) {
    this.orderService.getOrderCoffees(oid)
      .subscribe(coffees => {this.coffees = coffees;});
  }

  deleteOrder(id: number) {
    this.orderService.deleteOrder(id);
    window.location.reload();
  }

  goToUpdate(oid: number, ostatus: string, olocaldatetime: string) {
    this.router.navigateByUrl('/order-update', {state: {oid, ostatus, olocaldatetime}});
  }

  goToAddTo(oid: number, ostatus: string, olocaldatetime: string) {
    this.router.navigateByUrl('/order-add', {state: {oid, ostatus, olocaldatetime}});
  }
}
