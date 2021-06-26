import { Injectable } from '@angular/core';
import {HttpClient, HttpParams} from "@angular/common/http";
import {map} from "rxjs/operators";
import {Observable} from "rxjs";
import {Customer} from "./customer.model";

@Injectable({
  providedIn: 'root'
})
export class CustomerService {
  private customersUrl = 'http://localhost:8080/api/customers';

  constructor(private httpClient: HttpClient) { }

  getCustomers(): Observable<Customer[]> {
    return this.httpClient
      .get<Array<Customer>>(this.customersUrl);
  }

  saveCustomer(customer: Customer) {
    return this.httpClient.post<Customer>(this.customersUrl, customer);
  }

  deleteCustomer(customerId: number) {
    const url = `${this.customersUrl}/${customerId}`;
    return this.httpClient.delete(url).subscribe(v => console.log(v));
  }

  getCustomer(id: number): Observable<Customer> {
    // @ts-ignore
    return this.getCustomers()
      .pipe(
        map(customers => customers.find(customer => customer.id === id))
      );
  }

  updateCustomer(customer: Customer) {
    const url = `${this.customersUrl}/${customer.id}`;
    return this.httpClient
      .put<Customer>(url, customer).subscribe(v => console.log(v));
  }

  filterCustomersByName(name: string): Observable<Customer[]> {
    const url = `${this.customersUrl}/filterCustomersByName`;
    let params = new HttpParams();
    params = params.append("name", name);
    return this.httpClient.get<Array<Customer>>(url, {params: params});
  }

  filterCustomersByAgeInterval(age1: string, age2: string): Observable<Customer[]> {
    const url = `${this.customersUrl}/filterCustomersByAgeInterval`;
    let params = new HttpParams();
    params = params.append("age1", age1);
    params = params.append("age2", age2);
    return this.httpClient.get<Array<Customer>>(url, {params: params});
  }

}
