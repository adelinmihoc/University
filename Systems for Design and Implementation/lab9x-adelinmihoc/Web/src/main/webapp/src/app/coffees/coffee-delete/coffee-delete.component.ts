import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {AddressService} from "../../addresses/shared/address.service";
import {CoffeeService} from "../shared/coffee.service";

@Component({
  selector: 'app-coffee-delete',
  templateUrl: './coffee-delete.component.html',
  styleUrls: ['./coffee-delete.component.css']
})
export class CoffeeDeleteComponent implements OnInit {
  coffeeDeleteForm = new FormGroup({
    id: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ])
  });

  constructor(private coffeeService: CoffeeService) { }

  ngOnInit(): void {
  }

  onSubmitDeleteById(form: FormGroup) {
    if (form.valid) {
      this.coffeeService.deleteCoffee(form.value.id).subscribe(v => console.log(v));
    } else {
      alert("please enter a valid id");
    }
  }

  get id() {
    return this.coffeeDeleteForm.get('id');
  }

}
