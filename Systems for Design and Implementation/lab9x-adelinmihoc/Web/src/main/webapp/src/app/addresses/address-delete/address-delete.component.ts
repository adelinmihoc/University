import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {AddressService} from "../shared/address.service";

@Component({
  selector: 'app-address-delete',
  templateUrl: './address-delete.component.html',
  styleUrls: ['./address-delete.component.css']
})
export class AddressDeleteComponent implements OnInit {
  addressDeleteForm = new FormGroup({
    id: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ])
  });

  constructor(private addressService: AddressService) { }

  ngOnInit(): void {
  }

  onSubmitDeleteById(form: FormGroup) {
    if (form.valid) {
      this.addressService.deleteAddress(form.value.id);
    } else {
      alert("please enter a valid id");
    }
  }

  onSubmitDeleteByNumber(form: FormGroup) {
    if (form.valid) {
      this.addressService.deleteAddressesByNumber(form.value.id);
    } else {
      alert("please enter a valid number");
    }
  }

  get id() {
    return this.addressDeleteForm.get('id');
  }


}
