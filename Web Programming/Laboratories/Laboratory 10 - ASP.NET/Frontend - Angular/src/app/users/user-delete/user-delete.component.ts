import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {UserService} from "../Shared/user.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-user-delete',
  templateUrl: './user-delete.component.html',
  styleUrls: ['./user-delete.component.css']
})
export class UserDeleteComponent implements OnInit {
  userDeleteForm = new FormGroup({
    id: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ])
  });

  constructor(private userService: UserService, private router: Router) {
    if (localStorage.getItem("user") == null) {
      router.navigateByUrl("/login");
    }
  }

  ngOnInit(): void {
  }

  onSubmitDeleteById(form: FormGroup) {
    if (form.valid) {
      this.userService.deleteUser(form.value.id);
      this.router.navigateByUrl("/users");
    } else {
      alert("please enter a valid id");
    }
  }

  get id() {
    return this.userDeleteForm.get('id');
  }
}
