import { Component, OnInit } from '@angular/core';
import {Address} from "../shared/address.model";
import {AddressService} from "../shared/address.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-address-list',
  templateUrl: './address-list.component.html',
  styleUrls: ['./address-list.component.css']
})
export class AddressListComponent implements OnInit {
  addresses!: Address[];

  constructor(private addressService: AddressService, private router: Router) { }

  ngOnInit(): void {
    this.addressService.getAddresses()
      .subscribe(addresses => this.addresses = addresses);
  }

  deleteAddress(aid: number) {
    this.addressService.deleteAddress(aid);
    window.location.reload();
  }

  goToUpdate(aid: number, acity: string, astreet: string, anumber: number) {
    this.router.navigateByUrl('/address-update', {state: {aid, acity, astreet, anumber}});
  }
}
