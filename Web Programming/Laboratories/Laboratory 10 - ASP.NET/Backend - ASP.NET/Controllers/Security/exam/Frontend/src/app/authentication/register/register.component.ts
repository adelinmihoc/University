import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css']
})
export class RegisterComponent implements OnInit {
  registerForm = new FormGroup({
    username: new FormControl('', [
      Validators.required,
    ]),
    password: new FormControl('', [
      Validators.required,
    ])
  });

  constructor() { }

  ngOnInit(): void {
  }

  onSubmit(form: FormGroup) {
    console.log("valid?", form.valid);
    console.log("username", form.value.username);
    console.log("password", form.value.password);
    // if (form.valid) {
    //   const parent: Parent = <Parent>{field1: form.value.field1, field2: form.value.field2};
    //   this.parentService.save(parent).subscribe(v => console.log(v));
    // } else {
    //   alert("Please enter a valid parent");
    // }
  }

  get username() {
    return this.registerForm.get('username');
  }

  get password() {
    return this.registerForm.get('password');
  }

}
