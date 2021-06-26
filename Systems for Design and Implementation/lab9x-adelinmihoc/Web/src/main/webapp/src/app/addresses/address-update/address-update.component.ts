import { Component, OnInit } from '@angular/core';
import {Form, FormControl, FormGroup, Validators} from "@angular/forms";
import {ActivatedRoute, Router} from "@angular/router";
import {Subscription} from "rxjs";
import {AddressService} from "../shared/address.service";
import {Address} from "../shared/address.model";

@Component({
  selector: 'app-address-update',
  templateUrl: './address-update.component.html',
  styleUrls: ['./address-update.component.css']
})
export class AddressUpdateComponent implements OnInit {
  addressUpdateForm!: FormGroup;
  addressId = 0;
  addressCity = "";
  addressStreet = "";
  addressNumber = 0;


  constructor(private router: Router, private route: ActivatedRoute, private addressService: AddressService) {
    const navigation = this.router.getCurrentNavigation();
    if (navigation != null) {
      const state = navigation.extras.state as {
        aid: number,
        acity: string,
        astreet: string,
        anumber: number
      };
      console.log(state);
      this.addressId = state.aid;
      this.addressCity = state.acity;
      this.addressStreet = state.astreet;
      this.addressNumber = state.anumber;
    }
  }

  ngOnInit(): void {
    this.addressUpdateForm = new FormGroup({
      id: new FormControl(this.addressId,[
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ]),
      city: new FormControl(this.addressCity, [
        Validators.required,
        Validators.pattern('^[a-zA-Z]*$')
      ]),
      street: new FormControl(this.addressStreet, [
        Validators.required,
        Validators.pattern('^[a-zA-Z]*$')
      ]),
      number: new FormControl(this.addressNumber, [
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ])
    });
  }

  onSubmit(form: FormGroup) {
    // console.log("valid?", form.valid);
    // console.log("city ", form.value.city);
    // console.log("number ", form.value.number);
    // console.log("street ", form.value.street);
    if (form.valid) {
      const address: Address = <Address>{id: form.value.id, city: form.value.city,
        street: form.value.street, number: form.value.number};
      this.addressService.updateAddress(address);
    } else {
      alert("please enter a valid address");
    }
  }

  get city() {
    return this.addressUpdateForm.get('city');
  }

  get number() {
    return this.addressUpdateForm.get('number');
  }
  get street() {
    return this.addressUpdateForm.get('street');
  }

  get id() {
    return this.addressUpdateForm.get('id');
  }
}
