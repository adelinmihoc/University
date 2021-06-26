import { Injectable } from '@angular/core';
import {HttpClient, HttpParams} from "@angular/common/http";
import {map} from "rxjs/operators";
import {Observable} from "rxjs";
import {Address} from "./address.model";

@Injectable({
  providedIn: 'root'
})
export class AddressService {
  private addressesUrl = 'http://localhost:8080/api/addresses';

  constructor(private httpClient: HttpClient) {
  }

  getAddresses(): Observable<Address[]> {
    const addresses: Observable<Address[]> = this.httpClient
      .get<Array<Address>>(this.addressesUrl);
    console.log(addresses);
    return addresses;
  }

  saveAddress(address: Address) {
    console.log(address);
    return this.httpClient
      .post<Address>(this.addressesUrl, address, {observe: 'response'});
  }

  deleteAddress(addressId: number) {
    const url = `${this.addressesUrl}/${addressId}`;
    return this.httpClient.delete(url).subscribe(response => console.log(response));
  }

  deleteAddressesByNumber(no: number) {
    const url = `${this.addressesUrl}/deleteAddressByNumber`;
    let params = new HttpParams();
    params = params.append("number", no);
    return this.httpClient.delete(url, {params: params}).subscribe(v => console.log(v));

  }

  getAddress(id: number): Observable<Address> {
    // @ts-ignore
    return this.getAddresses()
      .pipe(
        map(addresses => addresses.find(address => address.id === id))
      );
  }

  updateAddress(address: Address) {
    const url = `${this.addressesUrl}/${address.id}`;
    return this.httpClient
      .put<Address>(url, address).subscribe(v => console.log(v));
  }
}
