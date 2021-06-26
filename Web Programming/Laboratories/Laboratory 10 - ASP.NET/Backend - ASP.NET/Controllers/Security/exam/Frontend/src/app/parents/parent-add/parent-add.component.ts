import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {ParentService} from "../shared/parent.service";
import {Parent} from "../shared/parent.model";

@Component({
  selector: 'app-parent-add',
  templateUrl: './parent-add.component.html',
  styleUrls: ['./parent-add.component.css']
})
export class ParentAddComponent implements OnInit {
  parentAddForm = new FormGroup({
    destination: new FormControl('', [
      Validators.required,
      Validators.pattern('^[a-zA-Z]*$')
    ]),
    country: new FormControl('', [
      Validators.required,
      Validators.pattern('^[a-zA-Z]*$')
    ]),
    price: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ])
  });

  constructor(private parentService: ParentService) { }

  ngOnInit(): void {
  }

  onSubmit(form: FormGroup) {
    // if (form.valid) {
    //   const parent: Parent = <Parent>{destination: form.value.destination, country: form.value.country, price: form.value.price};
    //   this.parentService.save(parent).subscribe(v => console.log(v));
    // } else {
    //   alert("Please enter a valid parent");
    // }
  }

  get destination() {
    return this.parentAddForm.get('destination');
  }

  get country() {
    return this.parentAddForm.get('country');
  }

  get price() {
    return this.parentAddForm.get('price');
  }

}
