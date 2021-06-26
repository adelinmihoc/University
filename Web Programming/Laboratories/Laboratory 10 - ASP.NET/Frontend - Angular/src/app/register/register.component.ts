import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {UserService} from "../users/Shared/user.service";
import {User} from "../users/Shared/user.model";
import {Router} from "@angular/router";

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
    ]),
    name: new FormControl('', [
      Validators.required,
      Validators.pattern('^[a-zA-Z]*$')
    ]),
    age: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ]),
    role: new FormControl('', [
      Validators.required,
    ]),
    profile: new FormControl('', [
      Validators.required,
    ]),
    email: new FormControl('', [
      Validators.required,
    ]),
    webpage: new FormControl('', [
      Validators.required,
    ])
  });

  constructor(private userService: UserService, private router: Router) { }

  ngOnInit(): void {
  }

  onSubmit(form: FormGroup) {
    console.log("valid?", form.valid);
    console.log("username:", form.value.username);
    console.log("password:", form.value.password);
    console.log("name:", form.value.name);
    console.log("age:", form.value.age);
    console.log("role:", form.value.role);
    console.log("profile:", form.value.profile);
    console.log("email:", form.value.email);
    console.log("webpage:", form.value.webpage);

    if (form.valid) {
      const user: User = <User>{username: form.value.username, password: form.value.password,
        name: form.value.name, age: form.value.age, role: form.value.role, profile: form.value.profile,
        email: form.value.email, webpage: form.value.webpage};
      this.userService.saveUser(user).subscribe(v => console.log(v));
      this.router.navigateByUrl("/login");
    } else {
      alert("Invalid credentials");
    }
  }

  get username() {
    return this.registerForm.get('username');
  }

  get password() {
    return this.registerForm.get('password');
  }

  get name() {
    return this.registerForm.get('name');
  }

  get age() {
    return this.registerForm.get('age');
  }

  get role() {
    return this.registerForm.get('role');
  }

  get profile() {
    return this.registerForm.get('profile');
  }

  get email() {
    return this.registerForm.get('email');
  }

  get webpage() {
    return this.registerForm.get('webpage');
  }
}
