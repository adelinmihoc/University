import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {ActivatedRoute, Router} from "@angular/router";
import {Coffee} from "../shared/coffee.model";
import {CoffeeService} from "../shared/coffee.service";

@Component({
  selector: 'app-coffee-update',
  templateUrl: './coffee-update.component.html',
  styleUrls: ['./coffee-update.component.css']
})
export class CoffeeUpdateComponent implements OnInit {
  coffeeUpdateForm!: FormGroup;
  coffeeId = 0;
  coffeeName = "";
  coffeeOrigin = "";
  coffeePrice = 0;
  coffeeQuantity = 0;


  constructor(private router: Router, private route: ActivatedRoute, private coffeeService: CoffeeService) {
    const navigation = this.router.getCurrentNavigation();
    if (navigation != null) {
      const state = navigation.extras.state as {
        cid: number,
        cname: string,
        corigin: string,
        cprice: number,
        cquantity: number
      };
      console.log(state);
      this.coffeeId = state.cid;
      this.coffeeName = state.cname;
      this.coffeeOrigin = state.corigin;
      this.coffeePrice = state.cprice;
      this.coffeeQuantity = state.cquantity;
    }
  }

  ngOnInit(): void {
    this.coffeeUpdateForm = new FormGroup({
      id: new FormControl(this.coffeeId,[
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ]),
      name: new FormControl(this.coffeeName, [
        Validators.required,
        Validators.pattern('^[a-zA-Z]*$')
      ]),
      origin: new FormControl(this.coffeeOrigin, [
        Validators.required,
        Validators.pattern('^[a-zA-Z]*$')
      ]),
      price: new FormControl(this.coffeePrice, [
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ]),
      quantity: new FormControl(this.coffeeQuantity, [
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ])
    });
  }

  onSubmit(form: FormGroup) {
    // console.log("valid?", form.valid);
    // console.log("id ", form.value.id);
    // console.log("name ", form.value.name);
    // console.log("origin ", form.value.origin);
    // console.log("price ", form.value.price);
    // console.log("quantity ", form.value.quantity);
    if (form.valid) {
      const coffee: Coffee = <Coffee>{id: form.value.id, name: form.value.name,
        origin: form.value.origin, price: form.value.price, quantity: form.value.quantity};
        this.coffeeService.updateCoffee(coffee).subscribe(v => console.log(v));
    } else {
      alert("please enter a valid coffee");
    }
  }

  get id() {
    return this.coffeeUpdateForm.get('id');
  }

  get name() {
    return this.coffeeUpdateForm.get('name');
  }

  get origin() {
    return this.coffeeUpdateForm.get('origin');
  }

  get price() {
    return this.coffeeUpdateForm.get('price');
  }

  get quantity() {
    return this.coffeeUpdateForm.get('quantity');
  }
}
