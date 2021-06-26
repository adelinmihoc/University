import { Component, OnInit } from '@angular/core';
import {UserService} from '../shared/user.service';
import {User} from '../shared/user.model';

@Component({
  selector: 'app-user-browse',
  templateUrl: './user-browse.component.html',
  styleUrls: ['./user-browse.component.css']
})
export class UserBrowseComponent implements OnInit {
  roles: string[];
  users: User[];

  constructor(private userService: UserService) { }

  ngOnInit(): void {
    this.getRoles();
  }

  // tslint:disable-next-line:typedef
  getRoles() {
    this.userService.getUserRoles().subscribe(roles => this.roles = roles);
  }

  // tslint:disable-next-line:typedef
  browseUsers(role: string) {
    this.userService.browseUsers(role).subscribe(users => this.users = users);
  }

}
