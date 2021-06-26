import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {CoffeeService} from "../shared/coffee.service";
import {Coffee} from "../shared/coffee.model";

@Component({
  selector: 'app-coffee-add',
  templateUrl: './coffee-add.component.html',
  styleUrls: ['./coffee-add.component.css']
})
export class CoffeeAddComponent implements OnInit {
  coffeeAddForm = new FormGroup({
    name: new FormControl('', [
      Validators.required,
      Validators.pattern('^[a-zA-Z]*$')
    ]),
    origin: new FormControl('', [
      Validators.required,
      Validators.pattern('^[a-zA-Z]*$')
    ]),
    price: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ])
    ,
    quantity: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ])
  });

  constructor(private coffeeService: CoffeeService) {
  }

  ngOnInit(): void {
  }

  onSubmit(form: FormGroup) {
    // console.log("valid?", form.valid);
    // console.log("name ", form.value.name);
    // console.log("origin ", form.value.origin);
    // console.log("price ", form.value.price);
    // console.log("quantity ", form.value.quantity);
    if (form.valid) {
      const coffee: Coffee = <Coffee>{name: form.value.name, origin: form.value.origin,
        price: form.value.price, quantity: form.value.quantity};
      this.coffeeService.saveCoffee(coffee).subscribe(v => console.log(v));
    } else {
      alert("please enter a valid coffee");
    }
  }

  get name() {
    return this.coffeeAddForm.get('name');
  }

  get origin() {
    return this.coffeeAddForm.get('origin');
  }

  get price() {
    return this.coffeeAddForm.get('price');
  }

  get quantity() {
    return this.coffeeAddForm.get('quantity');
  }
}
