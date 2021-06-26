import { Injectable } from '@angular/core';
import {HttpClient, HttpParams} from "@angular/common/http";
import {Coffee} from "./coffee.model";
import {map} from "rxjs/operators";
import {Observable} from "rxjs";

@Injectable({
  providedIn: 'root'
})
export class CoffeeService {
  private coffeesUrl = 'http://localhost:8080/api/coffees';

  constructor(private httpClient: HttpClient) { }

  getCoffees(): Observable<Coffee[]> {
    return this.httpClient.get<Array<Coffee>>(this.coffeesUrl);
  }

  saveCoffee(coffee: Coffee) {
    return this.httpClient.post<Coffee>(this.coffeesUrl, coffee, {observe: 'response'});
  }

  deleteCoffee(coffeeId: number) {
    const url = `${this.coffeesUrl}/${coffeeId}`;
    return this.httpClient
      .delete(url);
  }

  updateCoffee(coffee: Coffee) {
    const url = `${this.coffeesUrl}/${coffee.id}`;
    return this.httpClient
      .put<Coffee>(url, coffee);
  }

  getCoffee(id: number): Observable<Coffee> {
    // @ts-ignore
    return this.getCoffees()
      .pipe(
        map(coffees => coffees.find(coffee => coffee.id === id))
      );
  }

  filterCoffeeByOrigin(origin: string): Observable<Coffee[]> {
    const url = `${this.coffeesUrl}/filterCoffeesByOrigin`;
    let params = new HttpParams();
    params = params.append("origin", origin);
    return this.httpClient.get<Array<Coffee>>(url, {params: params});
  }
}
