import { Component, OnInit } from '@angular/core';
import {ActivatedRoute, Router} from "@angular/router";
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {ParentService} from "../shared/parent.service";
import {Parent} from "../shared/parent.model";

@Component({
  selector: 'app-parent-update',
  templateUrl: './parent-update.component.html',
  styleUrls: ['./parent-update.component.css']
})
export class ParentUpdateComponent implements OnInit {
  parentUpdateForm!: FormGroup;
  parentId = 0;
  parentDestination = "";
  parentCountry = "";
  parentPrice = 0;


  constructor(private router: Router, private route: ActivatedRoute, private parentService: ParentService) {
    const navigation = this.router.getCurrentNavigation();
    if (navigation != null) {
      const state = navigation.extras.state as {
        pid: number,
        pdestination: string,
        pcountry: string,
        pprice: number,
      };
      console.log(state);
      this.parentId = state.pid;
      this.parentDestination = state.pdestination;
      this.parentCountry = state.pcountry;
      this.parentPrice = state.pprice;
    }
  }

  ngOnInit(): void {
    this.parentUpdateForm= new FormGroup({
      id: new FormControl(this.parentId,[
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ]),
      destination: new FormControl(this.parentDestination, [
        Validators.required,
        Validators.pattern('^[a-zA-Z]*$')
      ]),
      country: new FormControl(this.parentCountry, [
        Validators.required,
        Validators.pattern('^[a-zA-Z]*$')
      ]),
      price: new FormControl(this.parentPrice, [
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ])
    });
  }

  onSubmit(form: FormGroup) {
    // if (form.valid) {
    //   const parent: Parent = <Parent>{id: form.value.id, destination: form.value.destination,
    //     country: form.value.country, price: form.value.price};
    //   this.parentService.update(parent);
    // } else {
    //   alert("please enter a valid parent");
    // }
  }

  get id() {
    return this.parentUpdateForm.get('id');
  }

  get destination() {
    return this.parentUpdateForm.get('destination');
  }

  get country() {
    return this.parentUpdateForm.get('country');
  }

  get price() {
    return this.parentUpdateForm.get('price');
  }
}
