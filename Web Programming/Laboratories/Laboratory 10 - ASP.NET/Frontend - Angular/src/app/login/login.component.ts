import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {AuthenticationService} from "../authentication/authentication.service";

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
    password: new FormControl('', [
      Validators.required,
    ])
  });

  constructor(private authenticationService: AuthenticationService) { }

  ngOnInit(): void {
  }

  onSubmit(form: FormGroup) {
    console.log("valid?", form.valid);
    console.log("username:", form.value.username);
    console.log("password:", form.value.password);

    if (form.valid) {
      const formData = {
        username: form.value.username,
        password: form.value.password
      }
      this.authenticationService.doLogin(formData);
    } else {
      alert("Invalid credentials");
    }
  }

  get username() {
    return this.loginForm.get('username');
  }

  get password() {
    return this.loginForm.get('password');
  }

}
