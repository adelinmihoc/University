import { Injectable } from '@angular/core';
import {HttpClient, HttpParams} from "@angular/common/http";
import {Coffee} from "../../coffees/shared/coffee.model";
import {map} from "rxjs/operators";
import {Observable} from "rxjs";
import {Order} from "./order.model";

@Injectable({
  providedIn: 'root'
})
export class OrderService {
  private ordersUrl = 'http://localhost:8080/api/orders';

  constructor(private httpClient: HttpClient) {
  }

  getOrders(): Observable<Order[]> {
    return this.httpClient
      .get<Array<Order>>(this.ordersUrl);
  }

  getOrderCoffees(oid: number): Observable<Coffee[]> {
    const url = `${this.ordersUrl}/${oid}/coffees`;
    return this.httpClient
      .get<Array<Coffee>>(url);
  }

  addCoffee(oid: number, cid: number) {
    const url = `${this.ordersUrl}/${oid}/coffees/${cid}`;
    return this.httpClient.put(url, null)
      .subscribe(v => console.log(v));
  }

  saveOrder(customerId: number) {
    let params = new HttpParams();
    params = params.append("customerId", customerId);
    return this.httpClient.post(this.ordersUrl, null, {params: params})
      .subscribe(v => console.log(v));
  }

  buyCoffee(orderId: string, coffeeId: string, quantity: string) {
    let params = new HttpParams();
    params = params.append("orderId", orderId);
    params = params.append("coffeeId", coffeeId);
    params = params.append("quantity", quantity);
    console.log(params);
    return this.httpClient.put(this.ordersUrl, null, {params: params});
  }

  getOrder(id: number): Observable<Order> {
    // @ts-ignore
    return this.getOrders()
      .pipe(
        map(orders => orders.find(order => order.id === id))
      );
  }

  filterCustomerCoffees(id: number): Observable<Coffee[]> {
    const url = `${this.ordersUrl}/filterCustomerCoffees`;
    let params = new HttpParams();
    params = params.append("customerId", id);
    return this.httpClient.get<Array<Coffee>>(url, {params: params});
  }

  filterCustomerOrders(id: number): Observable<Order[]> {
    const url = `${this.ordersUrl}/filterCustomerOrders`;
    let params = new HttpParams();
    params = params.append("customerId", id);
    return this.httpClient.get<Array<Order>>(url, {params: params});

  }

  deleteOrder(orderId: number) {
    const url = `${this.ordersUrl}/${orderId}`;
    return this.httpClient.delete(url)
      .subscribe(v => console.log(v));
  }

  changeStatus(id: string, status: string) {
    const url = `${this.ordersUrl}/${id}`;
    let params = new HttpParams();
    params = params.append("status", status);
    return this.httpClient.put(url, null, {params: params})
      .subscribe(v => console.log(v));
  }
}
