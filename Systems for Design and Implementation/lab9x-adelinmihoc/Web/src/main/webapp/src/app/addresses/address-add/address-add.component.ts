import {Component, OnInit} from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {AddressService} from "../shared/address.service";
import {Address} from "../shared/address.model";

@Component({
  selector: 'app-address-add',
  templateUrl: './address-add.component.html',
  styleUrls: ['./address-add.component.css']
})
export class AddressAddComponent implements OnInit {
  addressAddForm = new FormGroup({
    city: new FormControl('', [
      Validators.required,
      Validators.pattern('^[a-zA-Z]*$')
    ]),
    street: new FormControl('', [
      Validators.required,
      Validators.pattern('^[a-zA-Z]*$')
    ]),
    number: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ])
  });

  constructor(private addressService: AddressService) { }

  ngOnInit(): void {
  }

  onSubmit(form: FormGroup) {
    if (form.valid) {
      const address: Address = <Address>{city: form.value.city, street: form.value.street, number: form.value.number};
      this.addressService.saveAddress(address).subscribe(v => console.log(v));
    } else {
      alert("Please enter a valid address");
    }
  }

  get city() {
    return this.addressAddForm.get('city');
  }

  get number() {
    return this.addressAddForm.get('number');
  }
  get street() {
    return this.addressAddForm.get('street');
  }
}
