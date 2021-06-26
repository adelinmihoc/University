import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";
import {User} from "../Shared/user.model";
import {UserService} from "../Shared/user.service";


@Component({
  selector: 'app-user-list',
  templateUrl: './user-list.component.html',
  styleUrls: ['./user-list.component.css']
})
export class UserListComponent implements OnInit {
  users!: User[];

  constructor(private userService: UserService, private router: Router) {
    if (localStorage.getItem("user") == null) {
      router.navigateByUrl("/login");
    }
  }

  ngOnInit(): void {
    this.userService.getUsers()
      .subscribe(users => this.users = users);
  }

  deleteUser(uid: number) {
    this.userService.deleteUser(uid);
    window.location.reload();
  }

  goToUpdate(uid: number, uusername: string, upassword: string, uname: string, uage: number,
             urole: string, uprofile: string, uemail: string, uwebpage: string) {
    console.log("gotToUpdate function called");
    this.router.navigateByUrl('/user-update', {state: {uid, uusername, upassword, uname,
        uage, urole, uprofile, uemail, uwebpage}});
  }
}
