import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {AuthenticationService} from "../shared/authentication.service";


@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {
  loginForm = new FormGroup({
    username: new FormControl('', [
      Validators.required,
    ]),
  });

  constructor(private authenticationService: AuthenticationService) { }

  ngOnInit(): void {
  }

  onSubmit(form: FormGroup) {
    console.log("valid?", form.valid);
    console.log("username", form.value.username);

    if (form.valid) {
      this.authenticationService.doLogin(form.value.username);
    } else {
      alert("Please enter a valid username")
    }
    // if (form.valid) {
    //   const parent: Parent = <Parent>{field1: form.value.field1, field2: form.value.field2};
    //   this.parentService.save(parent).subscribe(v => console.log(v));
    // } else {
    //   alert("Please enter a valid parent");
    // }
  }

  get username() {
    return this.loginForm.get('username');
  }

}
