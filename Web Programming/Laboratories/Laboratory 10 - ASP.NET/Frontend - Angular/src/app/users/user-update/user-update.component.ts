import { Component, OnInit } from '@angular/core';
import {ActivatedRoute, Router} from "@angular/router";
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {UserService} from "../Shared/user.service";
import {User} from "../Shared/user.model";

@Component({
  selector: 'app-user-update',
  templateUrl: './user-update.component.html',
  styleUrls: ['./user-update.component.css']
})
export class UserUpdateComponent implements OnInit {
  userUpdateForm!: FormGroup;
  userId = 0;
  userUsername = "";
  userPassword = "";
  userName = "";
  userAge = 0;
  userRole = "";
  userProfile = "";
  userEmail = "";
  userWebpage = "";

  constructor(private router: Router, private route: ActivatedRoute, private userService: UserService) {
    if (localStorage.getItem("user") == null) {
      router.navigateByUrl("/login");
    }
    const navigation = this.router.getCurrentNavigation();
    if (navigation != null) {
      const state = navigation.extras.state as {
        uid: number,
        uusername: string,
        upassword: string,
        uname: string,
        uage: number,
        urole: string,
        uprofile: string,
        uemail: string,
        uwebpage: string
      }
      console.log(state);
      this.userId = state.uid;
      this.userUsername = state.uusername;
      this.userPassword = state.upassword;
      this.userName = state.uname;
      this.userAge = state.uage;
      this.userRole = state.urole;
      this.userProfile = state.uprofile;
      this.userEmail = state.uemail;
      this.userWebpage = state.uwebpage;
    }
  }

  ngOnInit(): void {
    this.userUpdateForm =  new FormGroup({
      id: new FormControl(this.userId, [
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ]),
      username: new FormControl(this.userUsername, [
        Validators.required,
      ]),
      password: new FormControl(this.userPassword, [
        Validators.required,
      ]),
      name: new FormControl(this.userName, [
        Validators.required,
      ]),
      age: new FormControl(this.userAge, [
        Validators.required,
        Validators.pattern('^[0-9]*$')
      ]),
      role: new FormControl(this.userRole, [
        Validators.required,
      ]),
      profile: new FormControl(this.userProfile, [
        Validators.required,
      ]),
      email: new FormControl(this.userEmail, [
        Validators.required,
      ]),
      webpage: new FormControl(this.userWebpage, [
        Validators.required,
      ])
    });
  }

  onSubmit(form: FormGroup) {
    console.log("valid?", form.valid);
    console.log("id", form.value.id);
    console.log("username:", form.value.username);
    console.log("password:", form.value.password);
    console.log("name:", form.value.name);
    console.log("age:", form.value.age);
    console.log("role:", form.value.role);
    console.log("profile:", form.value.profile);
    console.log("email:", form.value.email);
    console.log("webpage:", form.value.webpage);

    if (form.valid) {
      const user: User = <User>{id: form.value.id, username: form.value.username, password: form.value.password,
        name: form.value.name, age: form.value.age, role: form.value.role, profile: form.value.profile,
        email: form.value.email, webpage: form.value.webpage};
      this.userService.updateUser(user);
      this.router.navigateByUrl("/users");
    } else {
      alert("Invalid credentials");
    }
  }

  get id() {
    return this.userUpdateForm.get('id');
  }

  get username() {
    return this.userUpdateForm.get('username');
  }

  get password() {
    return this.userUpdateForm.get('password');
  }

  get name() {
    return this.userUpdateForm.get('name');
  }

  get age() {
    return this.userUpdateForm.get('age');
  }

  get role() {
    return this.userUpdateForm.get('role');
  }

  get profile() {
    return this.userUpdateForm.get('profile');
  }

  get email() {
    return this.userUpdateForm.get('email');
  }

  get webpage() {
    return this.userUpdateForm.get('webpage');
  }

}
