import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {User} from "../Shared/user.model";
import {UserService} from "../Shared/user.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-user-add',
  templateUrl: './user-add.component.html',
  styleUrls: ['./user-add.component.css']
})
export class UserAddComponent implements OnInit {
  userAddForm = new FormGroup({
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

  constructor(private userService: UserService, private router: Router) {
    if (localStorage.getItem("user") == null) {
      router.navigateByUrl("/login");
    }
  }

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
      this.router.navigateByUrl("/users");
    } else {
      alert("Invalid credentials");
    }
  }

  get username() {
    return this.userAddForm.get('username');
  }

  get password() {
    return this.userAddForm.get('password');
  }

  get name() {
    return this.userAddForm.get('name');
  }

  get age() {
    return this.userAddForm.get('age');
  }

  get role() {
    return this.userAddForm.get('role');
  }

  get profile() {
    return this.userAddForm.get('profile');
  }

  get email() {
    return this.userAddForm.get('email');
  }

  get webpage() {
    return this.userAddForm.get('webpage');
  }

}
