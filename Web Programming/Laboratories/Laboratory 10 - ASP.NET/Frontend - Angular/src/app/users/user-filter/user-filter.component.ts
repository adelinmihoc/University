import { Component, OnInit } from '@angular/core';
import {ActivatedRoute, Router} from "@angular/router";
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {UserService} from "../Shared/user.service";
import {User} from "../Shared/user.model";

@Component({
  selector: 'app-user-filter',
  templateUrl: './user-filter.component.html',
  styleUrls: ['./user-filter.component.css']
})
export class UserFilterComponent implements OnInit {
  filterForm!: FormGroup;
  filterRole = "";
  users!: User[];

  constructor(private userService: UserService, private router: Router) {
    if (localStorage.getItem("user") == null) {
      router.navigateByUrl("/login");
    }
  }

  ngOnInit(): void {
    this.filterForm = new FormGroup({
      role: new FormControl(this.filterRole, [
        Validators.required,
      ])
    });
  }

  onSubmit(form: FormGroup) {
    console.log("role is: ", form.value.role)
    if (form.valid) {
      this.userService.filterUsers(form.value.role)
        .subscribe(users => this.users = users);
    } else {
      alert("please enter a valid order");
    }
  }


  get role() {
    return this.filterForm.get('role');
  }

}
